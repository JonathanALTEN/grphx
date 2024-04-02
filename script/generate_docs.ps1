# Removing html folder
Write-Host "Removing html folder..."

Set-Location ..
Set-Location .\docs\

if (Test-Path html) {
    Remove-Item -Recurse -Force html
    Write-Host "html folder removed."
} else {
    Write-Host "html folder does not exist."
}

Write-Host "Done."

# Generating documentation
Write-Host "Generating documentation..."
doxygen

# Pause to keep the window open after execution (optional)
pause
