param (
    [string]$file,
    [string]$include,
    [string]$dir
)

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
Clear-Host

$compiler = ".\qawno\pawncc.exe"
$server = "omp-server.exe"
$now = Get-Date -Format "dd-MM-yyyy HH:mm:ss"

# Recursive search function
function Find-RootPwn([string]$currentFile) {
    $fileName = [System.IO.Path]::GetFileName($currentFile)
    
    # SUCCESS: If the file is a .pwn inside gamemodes or filterscripts
    if ($currentFile -match "gamemodes|filterscripts" -and $currentFile.EndsWith(".pwn")) {
        return $currentFile
    }

    # Search for files that include this module
    $parent = Get-ChildItem -Recurse -Include *.pwn, *.inc | 
              Select-String -Pattern "#include.*$($fileName.Replace('.', '\.'))" -List | 
              Select-Object -First 1

    if ($parent) { 
        return Find-RootPwn $parent.Path 
    } else { 
        # FAILED: No parent found, return the current file for final validation
        return $currentFile 
    }
}

# --- MINIMALIST HEADER ---
Write-Host ""
Write-Host " Initializing Compiler " -ForegroundColor White -BackgroundColor Cyan
Write-Host " Date: $now " -ForegroundColor Black -BackgroundColor Gray
Write-Host ""

Write-Host " > Tracking dependencies..." -ForegroundColor DarkGray
$targetFile = Find-RootPwn $file

if ($targetFile.EndsWith(".inc") -or ($targetFile -notmatch "gamemodes|filterscripts")) {
    Write-Host " [!] ERROR: This file is an orphan module!" -BackgroundColor Red -ForegroundColor White
    Write-Host " > No root .pwn file includes '$(Split-Path $file -Leaf)'." -ForegroundColor Yellow
    Write-Host " > Compilation aborted to prevent errors." -ForegroundColor Gray
    Write-Host ""
    exit
}

if (-not (Test-Path $targetFile)) {
    Write-Host " [!] ERROR: Target file path is invalid!" -BackgroundColor Red -ForegroundColor White
    exit
}

$targetDir = Split-Path $targetFile
$nameOnly = [System.IO.Path]::GetFileNameWithoutExtension($targetFile)
$outputPath = if ($targetFile -match "filterscripts") { "filterscripts\$nameOnly.amx" } else { "gamemodes\$nameOnly.amx" }

Write-Host " FILE " -NoNewline -ForegroundColor Black -BackgroundColor Gray
Write-Host " $(Split-Path $targetFile -Leaf)" -ForegroundColor White
Write-Host " DEST " -NoNewline -ForegroundColor Black -BackgroundColor Gray
Write-Host " $outputPath" -ForegroundColor DarkGray
Write-Host ""

# --- COMPILATION ---
$sw = [diagnostics.stopwatch]::StartNew()
# Run compiler
$output = & $compiler "$targetFile" "-i$include" "-D$targetDir" "-;+" "-(+" "-d3" 2>&1
$sw.Stop()

$elapsed = "{0:N2}" -f $sw.Elapsed.TotalSeconds

# --- RESULTS ---
if ($LASTEXITCODE -eq 0) {
    $fileInfo = Get-Item $outputPath
    $bytes = $fileInfo.Length
    $size = if ($bytes -ge 1GB) { "{0:N2} GB" -f ($bytes / 1GB) }
            elseif ($bytes -ge 1MB) { "{0:N2} MB" -f ($bytes / 1MB) }
            else { "{0:N2} KB" -f ($bytes / 1KB) }

    Write-Host " ---------------------------------------------------------- " -ForegroundColor Gray
    Write-Host " DONE " -NoNewline -ForegroundColor Black -BackgroundColor Green
    Write-Host " Compiled in $elapsed s | Size: $size" -ForegroundColor Green
    Write-Host ""

    if ($output) {
        $filtered = $output | Select-String -Pattern "warning"
        if ($filtered) {
            Write-Host " WARNINGS " -ForegroundColor Black -BackgroundColor Yellow
            Write-Host $filtered -ForegroundColor Yellow
            Write-Host ""
        }
    }

    # Sound
    powershell -c "[System.Media.SystemSounds]::Asterisk.Play()"

    # Variables
    $timeout = 60 # Seconds
    $counter = 0
    $keyPressed = $false
    $key = $null

    # Quick Action Menu
    Write-Host " [?] ACTION: " -NoNewline -ForegroundColor Cyan
    Write-Host "Press " -NoNewline -ForegroundColor Gray; Write-Host "[ENTER]" -ForegroundColor Yellow -NoNewline
    Write-Host " to launch server (Auto-exit in $timeout s)..." -ForegroundColor Gray
    
    while ($counter -lt ($timeout * 10)) {
        if ($Host.UI.RawUI.KeyAvailable) {
            $key = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
            $keyPressed = $true
            break
        }
        Start-Sleep -Milliseconds 100
        $counter++
        # if ($counter % 10 -eq 0) { 
        #     Write-Host "@" -NoNewline -ForegroundColor Gray -BackgroundColor Yellow
        # }
    }

    if ($keyPressed -and ($key.Key -eq 'Enter' -or $key.Character -eq [char]13)) {
        try {
            $fullPath = (Resolve-Path $server -ErrorAction Stop).Path
            $serverDir = Split-Path $fullPath
            Stop-Process -Name "omp-server" -ErrorAction SilentlyContinue
            
            $shell = New-Object -ComObject Shell.Application
            $shell.ShellExecute($fullPath, "", $serverDir, "open", 1)
            Write-Host "`n > Server started successfully!" -ForegroundColor Green
        } catch { 
            Write-Host "`n > Error: $server not found." -ForegroundColor Red 
        }
    } 
    else {
        Write-Host "`n > No action taken. Closing..." -ForegroundColor Gray
    }
} 
else 
{
    # Error Sound
    powershell -c "[System.Media.SystemSounds]::Hand.Play()"

    Write-Host " ---------------------------------------------------------- " -ForegroundColor Gray
    Write-Host " FAIL " -NoNewline -ForegroundColor White -BackgroundColor Red
    Write-Host " Build failed after $elapsed seconds." -ForegroundColor Red
    Write-Host ""
    if ($output) { 
        $output # Display Pawn Compiler errors
    } else {
        Write-Host " [!] CRITICAL: Compiler crash." -ForegroundColor Yellow
        Write-Host " Check: $targetFile" -ForegroundColor DarkGray
    }
}
Write-Host ""