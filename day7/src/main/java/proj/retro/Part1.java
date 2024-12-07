package proj.retro;

import java.io.IOException;

public class Part1 {

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            throw new IllegalArgumentException("Not enough arguments");
        }
        var combinator = new Combinator(args[0]);
        System.out.printf("The sum of the values is %d%n", combinator.sumValidCombinations());
    }

}
