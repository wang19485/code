package trivia;


import trivia.entities.Entity;
import trivia.gui.UIController;
import trivia.gui.panels.DummyScreen;

import javax.swing.*;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            UIController.queryRestrictions();
            UIController.showLoadingScreen();
            //build queries
            //execute queries
            UIController.showResults(null);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
