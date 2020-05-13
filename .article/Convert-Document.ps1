<#
.DESCRIPTION
Convert document with pandoc

.EXAMPLE
PS> Convert-Document -outFormat gfm
#>

Param(
  [string]$inFile = 'fachartikel.md',
  [string]$outFormat = 'commonmark',
  [string]$outDir = "out"
)

$outFileBaseName = $inFile.split('.')[0]
$outFile = "$outFileBaseName.$outFormat"
# add .md file extension for all markdown formats
if ($outFormat -in 'commonmark','gfm','markdown','markdown_github','markdown_mmd','markdown_phpextra','markdown_strict') {
  $outFile += ".md"
}
# set file extension to .tex for latex files
if ($outFormat -eq 'latex') {
  $outFile = "$outFileBaseName.tex"
}

if (-Not (Test-Path $outDir)) {
  $null = New-Item -Name $outDir -ItemType "directory"
}

$command = 'pandoc'
$command += " $inFile"
$command += ' --from markdown'
$command += " --to $outFormat"
$command += " --output $outDir/$outFile"
$command += ' --number-sections'
$command += ' --toc'
$command += ' --toc-depth=2'
$command += ' --standalone'
$command += ' -V toc-title=Inhaltsverzeichnis'
# $command += ' --metadata link-citations=true'

# use pandoc-citeproc for all formats except pdf
if ($outFormat -ne 'pdf') {
  $command += ' -F pandoc-citeproc'
  # $command += ' --csl din-1505-2-numeric.csl'
} else {
  $command += ' --biblatex'
  $command += ' --pdf-engine latexmk'
}

# use gitlab html template for html output
if ($outFormat -eq 'html') {
  $command += ' --template github.html'
}

Write-Host "creating $outFile" 
Write-Host $command
Invoke-Expression -Command $command




