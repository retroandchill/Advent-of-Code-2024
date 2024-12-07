package proj.retro;

import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Spliterator;
import java.util.StringTokenizer;
import java.util.regex.Pattern;
import java.util.stream.StreamSupport;

import static java.lang.Integer.parseInt;
import static java.lang.Long.parseLong;
import static java.util.Objects.requireNonNull;
import static java.util.Spliterators.spliteratorUnknownSize;

public class InputReader {

    private static final Pattern pattern = Pattern.compile("(\\d+): ((?:\\d+\\s*)+)");

    private InputReader() {}

    public static List<NumberInput> readInputs(String filename) throws IOException {
        try (var reader = InputReader.class.getClassLoader().getResourceAsStream(filename)) {
            requireNonNull(reader);
            return new BufferedReader(new InputStreamReader(reader)).lines()
                    .map(InputReader::parseInputLine)
                    .toList();
        }
    }

    private static NumberInput parseInputLine(String line) {
        var matcher = pattern.matcher(line);
        if (!matcher.find()) {
            throw new IllegalArgumentException("Invalid input: " + line);
        }

        return new NumberInput(parseLong(matcher.group(1)), parseNumbers(matcher.group(2)));
    }

    private static List<Long> parseNumbers(String numbers) {
        return Arrays.stream(numbers.split("\\s+"))
            .map(Long::parseLong)
            .toList();
    }

}
