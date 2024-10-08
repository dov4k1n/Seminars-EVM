package dev.dov4k1n.theater;

import java.util.List;

public class TheaterAlgorithmsPrint {

  /**
   * Prints detailed information of all Theaters in the list.
   * 
   * @param theaters the list of Theater objects to print
   */
  public static void print(List<Theater> theaters) {
    for (Theater theater : theaters) {
      theater.printShifted();
      System.out.println();
    }
  }

  /**
   * Prints names of all Theaters in the list.
   * 
   * @param theaters the list of Theater objects to print names from
   */
  public static void printNames(List<Theater> theaters) {
    for (Theater theater : theaters) {
      System.out.println("\t" + theater.getName());
    }
    System.out.println();
  }
}
