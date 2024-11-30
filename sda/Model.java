package sda;

import java.util.List;

public class Model {
    int noComments;
    List<String> comments;
    String publisher;
    String content;

    public Model(int noComments, List<String> comments, String publisher, String content) {
        this.noComments = noComments;
        this.comments = comments;
        this.publisher = publisher;
        this.content = content;
    }

    public int getNoComments() {
        return noComments;
    }

    public void setNoComments(int noComments) {
        this.noComments = noComments;
    }

    public List<String> getComments() {
        return comments;
    }

    public void setComments(List<String> comments) {
        this.comments = comments;
    }

    public String getPublisher() {
        return publisher;
    }

    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }



}
