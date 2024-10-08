package dev.dov4k1n.theater;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Implementation of rating algorithms for the class Theater.
 */
public class TheaterAlgorithmsRate {

  /**
   * Returns the theater with the highest rating.
   *
   * @param theaters the list of Theater objects
   * @return the Theater with the highest rating
   */
  public static Theater getMostRated(List<Theater> theaters) {
    Theater max = new Theater();

    for (Theater theater : theaters) {
      if (max.getRating() < theater.getRating()) {
        max = theater;
      }
    }

    return max;
  }

  /**
   * Returns a list of theaters with a rating higher than X.
   *
   * @param theaters the list of Theater objects
   * @param X the rating threshold
   * @return a list of Theaters with a rating greater than X
   */
  public static List<Theater> greaterThan(List<Theater> theaters, double X) {
    List<Theater> result = new ArrayList<>();

    for (Theater theater : theaters) {
      if (theater.getRating() > X) {
        result.add(theater);
      }
    }

    return result;
  }

  /**
   * Returns a list of theaters with a rating higher than the rating of the given theater's name.
   *
   * @param theaters the list of Theater objects
   * @param theaterName the name of the theater to compare ratings against
   * @return a list of Theaters with a rating greater than the given theater's rating
   * @throws IllegalArgumentException if the theater with the given name is not found
   */
  public static List<Theater> greaterThan(List<Theater> theaters, String theaterName) {
    Optional<Theater> givenTheater = theaters.stream()
      .filter(theater -> theater.getName().contains(theaterName))
      .findFirst();

    if (!givenTheater.isPresent()) {
      throw new IllegalArgumentException("No such theater with name: " + theaterName);
    }

    List<Theater> result = new ArrayList<>();

    for (Theater theater : theaters) {
      if (theater.getRating() > givenTheater.get().getRating()) {
        result.add(theater);
      }
    }

    return result;
  }
}
