<#
.DESCRIPTION
Convert document with pandoc

.EXAMPLE
PS> Convert-Document -outFormat gfm
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
  -N `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --toc `
  --toc-depth=2 `
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
  -N `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --template github.html `
  --toc `
  --toc-depth=2 `
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
  -N `
  -F pandoc-citeproc `
  --csl din-1505-2-numeric.csl `
  --toc `
  --toc-depth=2 `
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
  -N `
  -F pandoc-citeproc `
  -V toc-title:"Inhaltsverzeichnis" `
  --csl din-1505-2-numeric.csl `
  --toc `
  --toc-depth=2 `
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
  -N `
  --biblatex `
  --pdf-engine latexmk `
  --toc `
  --toc-depth=2 `
  -s `
  --from markdown `
  --to $outFormat `
  -o $outdir/$outFile  `
  $inFile
}




