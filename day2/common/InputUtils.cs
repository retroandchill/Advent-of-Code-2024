namespace common;

public class InputUtils {
    
    public static List<List<int>> ReadInput(string fileName) {
        using var file = File.OpenRead(fileName);
        var reader = new StreamReader(file);
        return reader.ReadToEnd()
            .Split(['\r', '\n'], StringSplitOptions.RemoveEmptyEntries)
            .Select(ReadLine)
            .ToList();
    }

    private static List<int> ReadLine(string line) {
        return line.Split(' ', StringSplitOptions.RemoveEmptyEntries)
            .Select(int.Parse)
            .ToList();
    }
    
}