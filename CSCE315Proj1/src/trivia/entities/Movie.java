package trivia.entities;

public class Movie implements Entity {
    String name;
    String releaseDate;
    String duration;
    String genres;
    String rating;

    public Movie(String name){
        this.name = name;
    }
    public Movie(String name, String releaseDate, String duration, String genres, String rating) {
        this.name = name;
        this.releaseDate = releaseDate;
        this.duration = duration;
        this.genres = genres;
        this.rating = rating;
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
