package proj.retro;

import com.google.common.collect.Sets;

import java.io.IOException;
import java.util.*;
import java.util.stream.IntStream;

import static java.lang.Math.pow;
import static java.util.stream.Collectors.*;
import static proj.retro.InputReader.readInputs;

public class Combinator {

    private List<NumberInput> inputs;

    public Combinator(String input) throws IOException {
        inputs = readInputs(input);
    }

    public long sumValidCombinations() {
        return inputs.stream()
                .filter(Combinator::hasValidCombination)
                .map(NumberInput::total)
                .reduce(0L, Long::sum);
    }

    public long sumValidCombinationsEnhanced() {
        return inputs.stream()
                .filter(Combinator::hasValidCombinationEnhanced)
                .map(NumberInput::total)
                .reduce(0L, Long::sum);
    }

    private static boolean hasValidCombination(NumberInput input) {
        var operators = List.of(Operator.ADD, Operator.MULTIPLY);
        return checkPossibleCombinations(input, operators);
    }

    private static boolean hasValidCombinationEnhanced(NumberInput input) {
        var operators = List.of(Operator.ADD, Operator.MULTIPLY, Operator.CONCAT);
        return checkPossibleCombinations(input, operators);
    }

    private static boolean checkPossibleCombinations(NumberInput input, List<Operator> operators) {
        int n = input.values().size() - 1;
        var factorPower = (int) pow(operators.size(), n);
        List<List<Operator>> operatorOptions = new ArrayList<>();
        for (int i = 0; i < factorPower; i++) {
            List<Operator> operatorsList = new ArrayList<>();
            for (int j = n - 1; j >= 0 ; j--) {
                var index = (i/(int) Math.pow(operators.size(), j))% operators.size();
                operatorsList.add(operators.get(index));
            }

            operatorOptions.add(operatorsList);
        }

        return operatorOptions.stream()
                .anyMatch(l -> tryOperate(input.values(), l) == input.total());
    }

    private static long tryOperate(List<Long> inputs, List<Operator> operators) {
        if (inputs.size() != operators.size() + 1) {
            throw new IllegalArgumentException("Invalid number of operators");
        }

        long total = inputs.getFirst();
        for (int i = 0; i < operators.size(); i++) {
            total = switch (operators.get(i)) {
                case ADD -> total + inputs.get(i + 1);
                case SUBTRACT -> total - inputs.get(i + 1);
                case MULTIPLY -> total * inputs.get(i + 1);
                case DIVIDE -> total / inputs.get(i + 1);
                case CONCAT -> Long.parseLong(Long.toString(total) + inputs.get(i + 1));
            };
        }
        return total;
    }

}
