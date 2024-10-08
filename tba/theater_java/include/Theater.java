/**
 * Class Theater implementation.
 */

package dev.dov4k1n.theater;

public class Theater {
  private static int count = 0;
  private int id;
  private String name;
  private String director;
  private String address;
  private double rating;

  /**
   * Constructor for Theater class.
   */
  public Theater(int id, String name, String director, String address, double rating) {
    this.id = id;
    this.name = name;
    this.director = director;
    this.address = address;
    this.rating = rating;
    count++;
  }

  /**
   * Copy constructor.
   */
  public Theater(Theater other) {
    this.id = other.id;
    this.name = other.name;
    this.director = other.director;
    this.address = other.address;
    this.rating = other.rating;
  }

  /**
   * Getter for theater's id.
   */
  public int getId() {
    return id;
  }

  /**
   * Getter for theater's name.
   */
  public String getName() {
    return name;
  }

  /**
   * Getter for theater's director.
   */
  public String getDirector() {
    return director;
  }

  /**
   * Getter for theater's address.
   */
  public String getAddress() {
    return address;
  }

  /**
   * Getter for theater's rating.
   */
  public double getRating() {
    return rating;
  }

  /**
   * Setter for theater's id.
   */
  public void setId(int newId) {
    this.id = newId;
  }

  /**
   * Setter for theater's name.
   */
  public void setName(String newName) {
    this.name = newName;
  }

  /**
   * Setter for theater's director.
   */
  public void setDirector(String newDirector) {
    this.director = newDirector;
  }

  /**
   * Setter for theater's address.
   */
  public void setAddress(String newAddress) {
    this.address = newAddress;
  }

  /**
   * Setter for theater's rating.
   */
  public void setRating(double newRating) {
    this.rating = newRating;
  }

  /**
   * Method to print theater's data.
   */
  public void print() {
    System.out.println("id: " + getId());
    System.out.println("name: " + getName());
    System.out.println("director: " + getDirector());
    System.out.println("address: " + getAddress());
    System.out.println("rating: " + getRating());
  }

  /**
   * Method to print theater's data with a tab prefix.
   */
  public void printShifted() {
    System.out.println("\t" + "id: " + getId());
    System.out.println("\t" + "name: " + getName());
    System.out.println("\t" + "director: " + getDirector());
    System.out.println("\t" + "address: " + getAddress());
    System.out.println("\t" + "rating: " + getRating());
  }

  /**
   * Static method to print field names.
   */
  public static void printFieldNames() {
    System.out.println("\t" + "id");
    System.out.println("\t" + "name");
    System.out.println("\t" + "director");
    System.out.println("\t" + "address");
    System.out.println("\t" + "rating");
  }
}
