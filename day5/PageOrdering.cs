using System.Text.RegularExpressions;

namespace day5;

public partial class PageOrdering {

    private readonly Dictionary<int, HashSet<int>> _orderRules = new();
    private readonly List<List<int>> _pageData = [];

    [GeneratedRegex(@"(\d+)\|(\d+)")]
    private static partial Regex RulesPattern();
    
    [GeneratedRegex(@"\d+(?:,\d+)*")]
    private static partial Regex PagesPattern();

    public PageOrdering(string filename) {
        using var file = File.OpenRead(filename);
        var reader = new StreamReader(file);
        var splitStrings = reader.ReadToEnd()
            .Split(['\r', '\n'], StringSplitOptions.RemoveEmptyEntries);
        foreach (var line in splitStrings) {
            ReadLine(line);
        }
    }
    
    private void ReadLine(string line) {
        var rulesPattern = RulesPattern();
        var rulesMatch = rulesPattern.Match(line);
        if (rulesMatch.Success) {
            var group1 = int.Parse(rulesMatch.Groups[1].Captures[0].Value);
            var group2 = int.Parse(rulesMatch.Groups[2].Captures[0].Value);
            if (!_orderRules.TryGetValue(group2, out var pages)) {
                pages = [];
                _orderRules.Add(group2, pages);
            }
            pages.Add(group1);
            return;
        }

        var pagesPatter = PagesPattern();
        var pagesMatch = pagesPatter.Match(line);
        if (pagesMatch.Success) {
            var pages = pagesMatch.Groups[0].Captures[0].Value.Split(',', StringSplitOptions.RemoveEmptyEntries)
                .Select(int.Parse)
                .ToList();
            _pageData.Add(pages);
        }
    }

    public int SumValidMiddles() {
        return _pageData
            .Where(IsValid)
            .Select(GetMiddle)
            .Sum();
    }
    
    public int SumInvalidMiddles() {
        return _pageData
            .Where(l => !IsValid(l))
            .Select(CorrectOrder)
            .Select(GetMiddle)
            .Sum();
    }
    
    private bool IsValid(List<int> pages) {
        for (int i = 0; i < pages.Count - 1; i++) {
            if (!_orderRules.TryGetValue(pages[i], out var validSet)) {
                continue;
            }

            for (int j = i + 1; j < pages.Count; j++) {
               if (validSet.Contains(pages[j])) {
                   return false;
               }
            }
        }
        
        return true;
    }

    private List<int> CorrectOrder(List<int> original) {
        var newList = new List<int>(original);
        for (int i = 0; i < newList.Count - 1; i++) {
            if (!_orderRules.TryGetValue(newList[i], out var validSet)) {
                continue;
            }

            for (int j = i + 1; j < newList.Count; j++) {
                if (validSet.Contains(newList[j])) {
                    (newList[i], newList[j]) = (newList[j], newList[i]);
                    i--;
                    break;
                }
            }
        }
        return newList;
    }

    private int GetMiddle(List<int> pages) {
        return pages[pages.Count / 2];
    }
    
}