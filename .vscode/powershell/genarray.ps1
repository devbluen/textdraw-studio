function Generate-Arrays-Interactive {
    # Prompting the user for input
    [int]$StartNumber = Read-Host "Enter the starting number"
    [int]$Columns     = Read-Host "Enter the number of columns (elements per array)"
    [int]$Count       = Read-Host "Enter the total number of arrays to generate"

    Write-Host "`n--- Generating Results ---" -ForegroundColor Cyan

    $currentValue = $StartNumber

    for ($i = 1; $i -le $Count; $i++) {
        $elements = @()
        
        # Populate the internal array
        for ($j = 0; $j -lt $Columns; $j++) {
            $elements += $currentValue
            $currentValue++
        }

        # Format the output as {n1, n2, n3}
        $arrayString = "{$($elements -join ', ')}"
        Write-Host "$arrayString"
    }
    
    Write-Host "--- Process Finished ---" -ForegroundColor Cyan
}

# Execute the function
Generate-Arrays-Interactive