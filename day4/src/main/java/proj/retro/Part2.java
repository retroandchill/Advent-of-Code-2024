package proj.retro;

import java.io.IOException;

public class Part2 {

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            throw new IllegalArgumentException("Wrong number of arguments");
        }

        var grid = new Grid(args[0]);

        System.out.println("Found %s repetitions".formatted(grid.findXmasPictures()));
    }

}
