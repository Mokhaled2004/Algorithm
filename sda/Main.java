package sda;

public class Main {

    public static void main(String[] args) {
        Model model = new Model(0, null, "Hassan", "YOLO !");
        View view = new View();
        Controller controller = new Controller(model, view);
        controller.setModelPublisher("Mohamed");
        controller.setModelContent("Hello");
        controller.updateView();
        controller.setModelPublisher("Marline");
        controller.setModelContent("Hi");
        controller.updateView();

    }
    
}
