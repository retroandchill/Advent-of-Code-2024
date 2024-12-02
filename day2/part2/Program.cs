// See https://aka.ms/new-console-template for more information

using common;

Console.Write("What file would you like to open: ");
var fileName = Console.ReadLine();
if (fileName == null)  {
    throw new ArgumentNullException(nameof(fileName));
}

Console.WriteLine($"Opening {fileName}");
var lines = InputUtils.ReadInput(fileName);
Console.WriteLine($"There are {SafetyValidator.CountSafe(lines, true)} safe lines");