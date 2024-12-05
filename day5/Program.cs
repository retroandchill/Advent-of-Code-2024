namespace day5;

class Program {
    static void Main(string[] args) {
        var ordering = new PageOrdering(args[0]);
        Console.WriteLine($"Correct sum: {ordering.SumValidMiddles()}");
        Console.WriteLine($"Invalid sum: {ordering.SumInvalidMiddles()}");
    }
}