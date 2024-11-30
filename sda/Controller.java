package sda;

public class Controller {

    private Model model;
    private View view;

    public Controller(Model model, View view) {
        this.model = model;
        this.view = view;
    }

    public void updateView() {
        view.printModelDetails(model.getNoComments(), model.getPublisher(), model.getContent());
    }

    public void setModelNoComments(int noComments) {
        model.setNoComments(noComments);
    }

    public void setModelPublisher(String publisher) {
        model.setPublisher(publisher);
    }

    public void setModelContent(String content) {
        model.setContent(content);
        model.noComments ++;
    }

    public int getModelNoComments() {
        return model.getNoComments();
    }

    public String getModelPublisher() {
        return model.getPublisher();
    }

    public String getModelContent() {
        return model.getContent();
    }





    
}
