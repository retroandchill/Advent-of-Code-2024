namespace common;

public class SafetyValidator {

    public static int CountSafe(List<List<int>> grid, bool dampen = false) {
        return grid.Count(i => CheckLine(i, dampen));
    }

    private static bool CheckLine(List<int> line, bool dampen = false) {
        var result = CheckLineRaw(line);
        if (result || !dampen) {
            return result;
        }
        
        return Enumerable.Range(0, line.Count)
            .Select(i => DampenLine(line, i))
            .Any(CheckLineRaw);
    }
    
    private static List<int> DampenLine(List<int> line, int index) {
        return line.Where((_, i) => i != index).ToList();
    }

    private static bool CheckLineRaw(List<int> line)
    {
        if (line.Count < 2) {
            throw new InvalidOperationException("Line must have at least 2 elements");
        }

        if (line[0] == line[1])
        {
            return false;
        }

        bool increasing = line[0] < line[1];
        for (int i = 1; i < line.Count; i++) {
            if (Math.Abs(line[i - 1] - line[i]) is > 3 or < 1)
            {
                return false;
            }

            if (increasing && line[i] < line[i - 1])
            {
                return false;
            }
            
            if (!increasing && line[i] > line[i - 1])
            {
                return false;
            }
        }

        return true;
    }
}