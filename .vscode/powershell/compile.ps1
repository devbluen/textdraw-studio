param (
    [string]$file,
    [string]$include,
    [string]$dir
)

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
Clear-Host

# Compiler and Server
$compiler   = ".\qawno\pawncc.exe"
$mode       = "omp-server"
$server     = $mode + ".exe"

# Variables Global
$currentPath = (Resolve-Path $file).Path
$now = Get-Date -Format "dd-MM-yyyy HH:mm:ss"
$foundRoot = $false
$targetFile = $null
$cursorPath = $currentPath
$cursorFindPath = $currentPath;
$currentFile = $(Split-Path $file -Leaf)

# Variables Paths [Book]
$projectRoot = $currentPath -replace "\\(gamemodes|filterscripts)\\.*", ""
$visited = @($currentPath)

# Header
Write-Host ""
Write-Host " Initializing Compiler " -ForegroundColor White -BackgroundColor Cyan
Write-Host " Date: $now " -ForegroundColor Black -BackgroundColor Gray
Write-Host " File: $currentFile " -ForegroundColor Black -BackgroundColor Gray
Write-Host ""
Write-Host " > Tracking dependencies..." -ForegroundColor DarkGray
Write-Host ""

# Find File
while ($true) {
    
    $relativeID = $cursorFindPath.Replace("$projectRoot\", "").Replace("\", "/")
    $shortID = $relativeID -replace "^(gamemodes|filterscripts)/", ""

    $parentDir = Split-Path $cursorPath -Parent
    $currentFolder = Split-Path $parentDir -Leaf;
    $isInBuildDir = $cursorPath -match "\\gamemodes\\|\\filterscripts\\"

    if (-not $parentDir -or -not ($parentDir.StartsWith($projectRoot))) { 
        Write-Host " > Limit reached: I exited the project folder." -ForegroundColor Yellow
        break 
    }

    # if (-not $parentDir -or $parentDir -notmatch "gamemodes|filterscripts|modulos") { break }

    $filesInFolder = Get-ChildItem -Path $parentDir -File | 
                    Where-Object { ($_.Extension -match "pwn|inc") -and ($visited -notcontains $_.FullName) }

    $escBase = [regex]::Escape($shortID)
    $pattern = "^\s*#include\s+[<""]?.*($escBase)(\.inc)?[>""]?"
    $match = $filesInFolder | Select-String -Pattern $pattern -List | Select-Object -First 1

    if($filesInFolder.Count -gt 0) {
        Write-Host " > Reading: $currentFolder ($($filesInFolder.Name -join ', '))" -ForegroundColor Gray
    }

    if ($cursorPath.EndsWith(".pwn") -and $isInBuildDir) {
        $targetFile = $cursorPath
        $foundRoot = $true
        break
    }

    if($match) 
    {
        Write-Host " > Success: $relativeID" -ForegroundColor Green

        $cursorPath = $match.Path
        $cursorFindPath = $match.Path
        $visited += $cursorPath
        $currentFile = Split-Path $cursorPath -Leaf     # Update currentFile to found

        if ($cursorPath.EndsWith(".pwn") -and $isInBuildDir) {
            $targetFile = $cursorPath
            $foundRoot = $true
            break
        }

        continue
    }

    $cursorPath = $parentDir
}

if (-not $foundRoot) {
    powershell -c "[System.Media.SystemSounds]::Hand.Play()"

    Write-Host ""
    Write-Host " ERROR " -BackgroundColor Red
    Write-Host " > No root .pwn file includes '$(Split-Path $file -Leaf)'." -ForegroundColor Yellow
    Write-Host " > Compilation aborted to prevent errors." -ForegroundColor Red
    Write-Host ""
    exit
}

if (-not (Test-Path $targetFile)) {
    Write-Host " [!] ERROR: Target file path is invalid!" -BackgroundColor Red -ForegroundColor White
    exit
}

$targetDir  = Split-Path $targetFile
$outputName = [System.IO.Path]::GetFileNameWithoutExtension($targetFile)
$outputPath = if ($targetFile -match "filterscripts") { "filterscripts\$outputName.amx" } else { "gamemodes\$outputName.amx" }

Write-Host ""
Write-Host " FILE " -NoNewline -ForegroundColor Black -BackgroundColor Gray
Write-Host " $(Split-Path $targetFile -Leaf)" -ForegroundColor White
Write-Host " DEST " -NoNewline -ForegroundColor Black -BackgroundColor Gray
Write-Host " $outputPath" -ForegroundColor DarkGray

$sw = [diagnostics.stopwatch]::StartNew()
$buildOutput = & $compiler "$targetFile" "-i$include" "-D$targetDir" "-;+" "-(+" "-d3" 2>&1
$sw.Stop()

$elapsed = "{0:N2}" -f $sw.Elapsed.TotalSeconds

if ($LASTEXITCODE -eq 0) {
    $fileInfo = Get-Item $outputPath
    $bytes = $fileInfo.Length
    $size = if ($bytes -ge 1GB) { "{0:N2} GB" -f ($bytes / 1GB) }
            elseif ($bytes -ge 1MB) { "{0:N2} MB" -f ($bytes / 1MB) }
            else { "{0:N2} KB" -f ($bytes / 1KB) }

    Write-Host ""
    Write-Host " DONE " -NoNewline -ForegroundColor Black -BackgroundColor Green
    Write-Host " Compiled in $elapsed s | Size: $size" -ForegroundColor Green
    
    if ($buildOutput) { 
        $filtered = $buildOutput | Select-String -Pattern "warning"
        if ($filtered) {
            Write-Host ""
            Write-Host " WARNINGS " -ForegroundColor Black -BackgroundColor Yellow
            
            $filtered | ForEach-Object {
                Write-Host $_.ToString().Trim() -ForegroundColor Yellow
            }
            
            Write-Host ""
        }
    }
    
    # Sound
    powershell -c "[System.Media.SystemSounds]::Asterisk.Play()"

    # Variables
    Write-Host " ACTION " -NoNewline -BackgroundColor Cyan -ForegroundColor White
    Write-Host " Press " -NoNewline -ForegroundColor Gray; 
    Write-Host "[ENTER]" -ForegroundColor Green -NoNewline
    Write-Host " to launch server..." -ForegroundColor Gray

    $timeout = 10 # segundos
    $timer = [System.Diagnostics.Stopwatch]::StartNew()
    $keyPressed = $false

    # Loop aguardando tecla ou timeout
    while ($timer.Elapsed.TotalSeconds -lt $timeout) {
        if ($Host.UI.RawUI.KeyAvailable) {
            $key = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
            if ($key.VirtualKeyCode -eq 13) {
                $keyPressed = $true
                break
            }
        }
        Start-Sleep -Milliseconds 100
    }
    $timer.Stop()

    if ($keyPressed) {
        try {
            $fullServerPath = (Resolve-Path $server).Path
            $serverDir = Split-Path $fullServerPath
            Stop-Process -Name $mode -ErrorAction SilentlyContinue

            $shell = New-Object -ComObject Shell.Application
            $shell.ShellExecute($fullServerPath, "", $serverDir, "open", 1)
            Write-Host "`n > Server started successfully!" -ForegroundColor Green   
        }
        catch {
            Write-Host "`n > Error: $server not found." -ForegroundColor Red 
        }
    }
    else {
        Write-Host "`n > Time's up. Operation cancelled." -ForegroundColor Yellow
    }
} 
else 
{
    powershell -c "[System.Media.SystemSounds]::Hand.Play()"

    Write-Host " ---------------------------------------------------------- " -ForegroundColor Gray
    Write-Host " FAIL " -NoNewline -ForegroundColor White -BackgroundColor Red
    Write-Host " Build failed after $elapsed seconds." -ForegroundColor Red
    Write-Host ""

    if ($buildOutput) {
        $importantLines = $buildOutput | Where-Object { $_ -match "error|warning" }
        if ($importantLines) {
            foreach ($line in $importantLines) {
                if ($line -match "error") {
                    Write-Host $line.ToString().Trim() -ForegroundColor Red
                } else {
                    Write-Host $line.ToString().Trim() -ForegroundColor Yellow
                }
            }
        } else {
            $buildOutput
        }
    } else {
        Write-Host " [!] CRITICAL: Compiler crash." -ForegroundColor Yellow
        Write-Host " Check: $targetFile" -ForegroundColor DarkGray
    }
}