# Get the current directory of the script
$currentDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Navigate to the parent directory (bin\Debug)
$parentDir = Split-Path -Parent $currentDir
$debugDir = Join-Path -Path $parentDir -ChildPath "bin\Debug"
Set-Location -Path $debugDir

# Get all .exe files in the current directory
$exeFiles = Get-ChildItem -Filter *.exe

# Check if there are any .exe files
if ($exeFiles.Count -eq 0) {
    Write-Host "No .exe files found in bin\Debug directory."
}
else {
    # Iterate through each .exe file
    foreach ($file in $exeFiles) {
        # Execute the .exe file
        & $file.FullName
    }
}
