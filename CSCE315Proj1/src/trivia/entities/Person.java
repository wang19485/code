package trivia.entities;

public class Person implements Entity {
    String name;
    String birthYear;
    String deathYear;
    String topProfessions;
    String relatedJob;

    public Person(String name) {
        this.name = name;
    }

    public Person(String name, String birthYear, String deathYear, String topProfessions, String relatedJob) {
        this.name = name;
        this.birthYear = birthYear;
        this.deathYear = deathYear;
        this.topProfessions = topProfessions;
        this.relatedJob = relatedJob;
    }

    @Override
    public String getResult() {
        return null;
    }

    @Override
    public String getQuery() {
        return null;
    }
}
