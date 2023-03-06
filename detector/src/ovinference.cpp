//
// Created by quonone on 23-2-17.
//
#include "../include/detector/ovinference.h"
#include <opencv2/dnn.hpp>
OvInference::OvInference(const std::string &model_path) :
        model_path_(model_path) {

    ov::Core core;
    model = core.read_model(model_path_);
    ov::preprocess::PrePostProcessor ppp = ov::preprocess::PrePostProcessor(model);
    ppp.input().tensor().set_element_type(ov::element::u8).set_layout("NHWC").set_color_format(
            ov::preprocess::ColorFormat::BGR);
    ppp.input().preprocess().convert_element_type(ov::element::f32).convert_color(
            ov::preprocess::ColorFormat::RGB).scale({255., 255., 255.});
    //  Specify model's input layout
    ppp.input().model().set_layout("NCHW");
    // Specify output results format
    ppp.output().tensor().set_element_type(ov::element::f32);
    // Embed above steps in the graph
    model = ppp.build();
    compiled_model = core.compile_model(model, "GPU");
}

OvInference::Resize OvInference::resize_and_pad(cv::Mat &img, cv::Size new_shape){
    float width = img.cols;
    float height = img.rows;
    float r = float(new_shape.width / std::max(width, height));
    int new_unpadW = int(round(width * r));
    int new_unpadH = int(round(height * r));
    Resize resize;
    cv::resize(img, resize.resized_image, cv::Size(new_unpadW, new_unpadH), 0, 0, cv::INTER_AREA);

    resize.dw = new_shape.width - new_unpadW;
    resize.dh = new_shape.height - new_unpadH;
    cv::Scalar color = cv::Scalar(100, 100, 100);
    cv::copyMakeBorder(resize.resized_image, resize.resized_image, 0, resize.dh, 0, resize.dw, cv::BORDER_CONSTANT,
                       color);

    return resize;
}

void OvInference::restore_scale(Detection &detection, float rx, float ry) {
    detection.obj.box.x *= rx;
    detection.obj.box.y *= ry;
    detection.obj.box.width *= rx;
    detection.obj.box.height *= ry;
    detection.obj.p1.x *= rx;
    detection.obj.p1.y *= ry;
    detection.obj.p2.x *= rx;
    detection.obj.p2.y *= ry;
    detection.obj.p3.x *= rx;
    detection.obj.p3.y *= ry;
    detection.obj.p4.x *= rx;
    detection.obj.p4.y *= ry;
}

void OvInference::infer(cv::Mat &img , std::vector<Detection>& final_result) {
    Resize res = resize_and_pad(img, cv::Size(640, 640));

    float *input_data = (float *) res.resized_image.data;
    ov::Tensor input_tensor = ov::Tensor(compiled_model.input().get_element_type(), compiled_model.input().get_shape(),
                                         input_data);
    ov::InferRequest infer_request = compiled_model.create_infer_request();
    infer_request.set_input_tensor(input_tensor);
    infer_request.infer();

    //Step 7. Retrieve inference results
    const ov::Tensor &output_tensor = infer_request.get_output_tensor();
    ov::Shape output_shape = output_tensor.get_shape();
    float *detections = output_tensor.data<float>();

    // std::cout<< "tensor shape "<<output_shape<<std::endl;


    std::vector<cv::Rect> boxes; //用于NMS
    std::vector<Obj> objs;
    std::vector<int> class_ids;
    std::vector<float> confidences;
    //遍历每一个候选结果
    // x,y,w,h,conf, x1,y1,x2,y2,x3,y3,x4,y4, c1,c2,c3, ... , c36
    for (int i = 0; i < output_shape[1]; i++) {
        float *detection = &detections[i * output_shape[2]];
        float confidence = detection[4];
        //选择置信度大于0.6的
        if (confidence >= CONFIDENCE_THRESHOLD) {
            //对于原来的yolo5,前五个后面是各个的类别
            // 但是对于yoloface，应该是第13个开始
            float *classes_scores = &detection[13];
            //生成每一个类别对应分数的矩阵，
            cv::Mat scores(1, output_shape[2] - 13, CV_32FC1, classes_scores);
            cv::Point class_id;
            double max_class_score;
            //找到最大分数的位置，即预测类别
            cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            //如果大于分数
            if (max_class_score > SCORE_THRESHOLD) {
                //按原来的顺序，存储下来（置信度）
                confidences.push_back(confidence);
                //每一个对应的类别标签的位置
                class_ids.push_back(class_id.x);

                float x = detection[0];
                float y = detection[1];
                float w = detection[2];
                float h = detection[3];
                // 1 2 3 4
                // lu ld rd rp
                cv::Point2f p1 = cv::Point2f(detection[5], detection[6]);
                cv::Point2f p2 = cv::Point2f(detection[7], detection[8]);
                cv::Point2f p3 = cv::Point2f(detection[9], detection[10]);
                cv::Point2f p4 = cv::Point2f(detection[11], detection[12]);
                float xmin = x - (w / 2);
                float ymin = y - (h / 2);

                boxes.push_back(cv::Rect(xmin, ymin, w, h));
                Obj obj = {cv::Rect(xmin, ymin, w, h), p1,p2,p3,p4};
                objs.push_back(obj);
            }
        }
    }

    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);

    std::vector<Detection> output;
    for (int i = 0; i < nms_result.size(); i++) {
        Detection result;
        int idx = nms_result[i];
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.obj = objs[idx];
        output.push_back(result);
    }


    // Step 9. Print results and save Figure with detections
    // more armor points
    for (int i = 0; i < output.size(); i++) {
        auto detection = output[i];
        auto box = detection.obj.box;
        auto classId = detection.class_id;
        auto confidence = detection.confidence;
        float rx = (float) img.cols / (float) (res.resized_image.cols - res.dw);
        float ry = (float) img.rows / (float) (res.resized_image.rows - res.dh);

        restore_scale(detection, rx, ry);
        final_result.push_back(detection);
//        std::cout << "Bbox" << i + 1 << ": Class: " << classId << " "
//             << "Confidence: " << confidence << " Scaled coords: [ "
//             << "cx: " << (float) (detection.obj.box.x + (detection.obj.box.width / 2)) / img.cols << ", "
//             << "cy: " << (float) (detection.obj.box.y + (detection.obj.box.height / 2)) / img.rows << ", "
//             << "w: " << (float) detection.obj.box.width / img.cols << ", "
//             << "h: " << (float) detection.obj.box.height / img.rows << " ]" << std::endl;
        float xmax = detection.obj.box.x + detection.obj.box.width;
        float ymax = detection.obj.box.y + detection.obj.box.height;
//        cv::rectangle(img, cv::Point(detection.obj.box.x, detection.obj.box.y), cv::Point(xmax, ymax), cv::Scalar(0, 255, 0), 3);
//        cv::rectangle(img, cv::Point(detection.obj.box.x, detection.obj.box.y - 20), cv::Point(xmax, detection.obj.box.y), cv::Scalar(0, 255, 0), cv::FILLED);
        cv::putText(img, std::to_string(classId), cv::Point(detection.obj.box.x, detection.obj.box.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    cv::Scalar(0, 255, 0), 2);
//        cv::circle(img,detection.obj.p1, 5, cv::Scalar (0,0,255),-1);
//        cv::circle(img,detection.obj.p2, 5, cv::Scalar (0,255,0),-1);
//        cv::circle(img,detection.obj.p3, 5, cv::Scalar (255,0,0),-1);
//        cv::circle(img,detection.obj.p4, 5, cv::Scalar (0,0,0),-1);

//        cv::line(img, detection.obj.p1, detection.obj.p3, cv::Scalar(0, 0, 255), 3);
//        cv::line(img, detection.obj.p2, detection.obj.p4, cv::Scalar(0, 0, 255), 3);
//        cv::line(img, detection.obj.p1, detection.obj.p2, cv::Scalar(0, 0, 255), 3);
//        cv::line(img, detection.obj.p3, detection.obj.p4, cv::Scalar(0, 0, 255), 3);
    }
}
