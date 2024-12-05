package proj.retro;

import java.util.List;
import java.util.stream.Stream;

public record Point(int x, int y) {

    public Point(List<Integer> ints) {
        this(ints.getFirst(), ints.getLast());
        if (ints.size() != 2) {
            throw new IllegalArgumentException("Points must have exactly two numbers");
        }
    }

    public boolean isZero() {
        return x == 0 && y == 0;
    }

    public Point add(Point other) {
        return new Point(x + other.x, y + other.y);
    }

    public Point add(Point... others) {
        return Stream.of(others).reduce(this, Point::add);
    }

    public Point subtract(Point other) {
        return new Point(x - other.x, y - other.y);
    }
}
