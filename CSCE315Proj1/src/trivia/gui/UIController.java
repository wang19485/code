package trivia.gui;

import trivia.entities.Entity;
import trivia.gui.panels.*;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class UIController {
    private static JFrame window;
    private static String searchTarget;
    private static List<Entity> restrictions;
    private static Boolean takingInput;
    static {
        window = new JFrame("Trivia Search!");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        restrictions = new ArrayList<>();
    }

    public static void setSearchTarget(String searchTarget){
        UIController.searchTarget= searchTarget;
    }

    public static String getSearchTarget(){
        return UIController.searchTarget;
    }

    public static void addRestriction(Entity restriction){
        restrictions.add(restriction);
    }

    public static void signalInputEnd(){
        synchronized (takingInput) {
            takingInput.notify();
        }
        takingInput = false;
    }

    public static void clearRestrictions(){
        restrictions.clear();
    }

    public static void showStartScreen(){
        window.setContentPane(new StartScreen().getPanel());
        window.pack();
        window.setVisible(true);
    }

    public static void showRestrictionTypeScreen(){
        window.setContentPane(new RestrictionTypeScreen().getPanel());
        window.pack();
        window.setVisible(true);
    }

    public static void showMovieRestrictionScreen(){
        window.setContentPane(new MovieRestrictionScreen().getPanel());
        window.pack();
        window.setVisible(true);
    }
    public static void showPersonRestrictionScreen(){
        window.setContentPane(new PersonRestrictionScreen().getPanel());
        window.pack();
        window.setVisible(true);
    }

    public static void showLoadingScreen(){
        window.setContentPane(new LoadingScreen().getPanel());
        window.pack();
        window.setVisible(true);
    }

    public static List<Entity> getRestrictions() {
        return restrictions;
    }

    public static void showResults(List<Entity> results){
        // go through result list
    }

    public static List<Entity> queryRestrictions() throws InterruptedException {
        takingInput = true;
        showStartScreen();
        synchronized(takingInput) {
            takingInput.wait(); // wait until GUI says input is done being taken
        }
        return restrictions;
    }
}
