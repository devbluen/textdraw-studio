
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$OutputEncoding = [System.Text.Encoding]::UTF8
Clear-Host

Write-Host "--- Math Textdraw Proporcional ---" -ForegroundColor Cyan

$tdLargura = Read-Host "X"
$tdAltura = Read-Host "Y"

$proporcao = [double]$tdAltura / [double]$tdLargura

$psAltura512 = [math]::Round(512 * $proporcao)
$psAltura1024 = [math]::Round(1024 * $proporcao)
Write-Host "`n--- Result ---" -ForegroundColor Yellow
Write-Host "Qualidade Média: 512px x $psAltura512 px"
Write-Host "Qualidade Alta: 1024px x $psAltura1024 px"
Write-Host "----------------------------------"

Write-Host "`nDica: Use o tamanho acima para criar o seu documento no PS." -ForegroundColor Gray
Read-Host "`nPressione Enter para sair"