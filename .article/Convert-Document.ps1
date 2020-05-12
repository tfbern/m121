<#
.DESCRIPTION
Convert document with pandoc

.EXAMPLE
PS> Convert.ps1
#>

Param(
  [string]$inFile = 'fachartikel.md',
  [string]$outFormat = 'html',
  [string]$outdir = "out"
)

$outFile = "$inFile.$outFormat"

if (-Not (Test-Path $outdir)) {
  $null = New-Item -Name $outdir -ItemType "directory"
}

if ($outFormat -eq 'gfm') {
  $outFile = "$($inFile.split('.')[0]).gfm.md"
  Write-Host "creating $outFile" 
  pandoc `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --toc `
  --metadata link-citations=true `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}

if ($outFormat -eq 'html') {
  Write-Host "creating $outFile" 
  pandoc `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --template github.html `
  --toc `
  --metadata link-citations=true `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}

if ($outFormat -eq 'docx') {
  Write-Host "creating $outFile" 
  pandoc `
  -F pandoc-citeproc `
  --csl din-1505-2-numeric.csl `
  --toc `
  --metadata link-citations=true `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}

if ($outFormat -eq 'latex') {
  Write-Host "creating $outFile" 
  pandoc `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --toc `
  --metadata link-citations=true `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}

if ($outFormat -eq 'pdf') {
  Write-Host "creating $outFile" 
  pandoc `
  --biblatex `
  --pdf-engine latexmk `
  --toc `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}




