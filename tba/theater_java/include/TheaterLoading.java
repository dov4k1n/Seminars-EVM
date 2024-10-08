package dev.dov4k1n.theater;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.ObjectNode;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TheaterLoading {

  /**
   * Loads theaters from a JSON file.
   *
   * @param inputPath the path to the input JSON file
   * @return a list of Theater objects
   * @throws IOException if an I/O error occurs
   */
  public static List<Theater> loadTheatersFrom(String inputPath) throws IOException {
    ObjectMapper objectMapper = new ObjectMapper();
    JsonNode rootNode = objectMapper.readTree(new File(inputPath));
    ArrayNode theatersArray = (ArrayNode) rootNode.get("theaters");

    List<Theater> result = new ArrayList<>();

    for (JsonNode theaterNode : theatersArray) {
      Theater theater = new Theater(
        theaterNode.get("id").asInt(),
        theaterNode.get("name").asText(),
        theaterNode.get("director").asText(),
        theaterNode.get("address").asText(),
        theaterNode.get("rating").asDouble()
      );
      result.add(theater);
    }

    return result;
  }

  /**
   * Saves a list of theaters to a JSON file.
   *
   * @param outputPath the path to the output JSON file
   * @param theaters   the list of Theater objects to save
   * @throws IOException if an I/O error occurs
   */
  public static void saveTheatersTo(String outputPath, List<Theater> theaters) throws IOException {
    ObjectMapper objectMapper = new ObjectMapper();
    ObjectNode rootNode = objectMapper.createObjectNode();
    ArrayNode theatersArray = objectMapper.createArrayNode();

    for (Theater theater : theaters) {
      ObjectNode theaterNode = objectMapper.createObjectNode();
      theaterNode.put("id", theater.getId());
      theaterNode.put("name", theater.getName());
      theaterNode.put("director", theater.getDirector());
      theaterNode.put("address", theater.getAddress());
      theaterNode.put("rating", theater.getRating());
      theatersArray.add(theaterNode);
    }

    rootNode.set("theaters", theatersArray);

    objectMapper.writerWithDefaultPrettyPrinter().writeValue(new File(outputPath), rootNode);
  }
}
