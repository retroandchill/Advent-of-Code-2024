package proj.retro;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Stream;

import com.google.common.collect.Sets;

import static java.util.Objects.requireNonNull;

public class Grid {

    private final char[][] grid;

    public Grid(String fileName) throws IOException {
        try (var fileContents = Grid.class.getClassLoader().getResourceAsStream(fileName)) {
            requireNonNull(fileContents);
            var reader = new BufferedReader(new InputStreamReader(fileContents));
            grid = reader.lines()
                    .map(String::toCharArray)
                    .toArray(char[][]::new);
        }
    }

    public long findXmasWords() {
        long count = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                count += checkForXmas(i, j);
            }
        }

        return count;
    }

    public long findXmasPictures() {
        long count = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                count += checkForXmasGrid(i, j);
            }
        }
        return count;
    }

    private long checkForXmas(int x, int y) {
        if (!checkForLetter('X', x, y)) {
            return 0;
        }

        var origin = new Point(x, y);
        return checkAdjacentPointsForLetter('M', x, y)
                .filter(p -> checkForLetter('A', origin.add(p, p)))
                .filter(p -> checkForLetter('S', origin.add(p, p, p)))
                .count();
    }

    private long checkForXmasGrid(int x, int y) {
        if (!checkForLetter('A', x, y)) {
            return 0;
        }

        var origin = new Point(x, y);
        var offsets = new TreeSet<>(List.of(-1, 1));
        var product = Sets.cartesianProduct(offsets, offsets);
        var results = product.stream()
                .map(Point::new)
                .map(origin::add)
                .filter(p -> checkForLetter('S', p) || checkForLetter('M', p))
                .toList();
        if (results.size() != 4) {
            return 0;
        }

        var mCount = results.stream()
                .filter(p -> checkForLetter('M', p))
                .count();
        var sCount = results.stream()
                .filter(p -> checkForLetter('S', p))
                .count();
        if (mCount != sCount) {
            return 0;
        }

        var letters = results.stream()
                .map(p -> grid[p.x()][p.y()])
                .toList();
        if (letters.get(0) != letters.get(1) && letters.get(0) != letters.get(2)) {
            return 0;
        }


        return 1;
    }

    private boolean checkForLetter(char letter, int x, int y) {
        if (x < 0 || x >= grid.length || y < 0 || y >= grid[0].length) {
            return false;
        }

        return grid[x][y] == letter;
    }

    private boolean checkForLetter(char letter, Point p) {
        return checkForLetter(letter, p.x(), p.y());
    }

    private Stream<Point> checkAdjacentPointsForLetter(char letter, int x, int y) {
        var origin = new Point(x, y);
        return getAdjacentPoints(x, y)
                .filter(p -> checkForLetter(letter, p.x(), p.y()))
                .map(p -> p.subtract(origin));
    }

    private Stream<Point> getAdjacentPoints(int x, int y) {
        var currentPosition = new Point(x, y);
        var offsets = Set.of(-1, 0, 1);
        var products = Sets.cartesianProduct(offsets, offsets);
        return products.stream()
                .map(Point::new)
                .filter(p -> !p.isZero())
                .map(p -> p.add(currentPosition))
                .filter(p -> p.x() >= 0 && p.x() < grid.length && p.y() >= 0 && p.y() < grid[x].length);

    }
}
