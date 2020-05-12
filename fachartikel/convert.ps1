$outdir = "formats"
if (-Not (Test-Path $outdir)) {
  $null = New-Item -Name $outdir -ItemType "directory"
}

$formats = $(pandoc --list-output-formats)
$numberofFormats = $formats.length
Write-Host "$numberofFormats output formats will be generated:"
$formats | ForEach-Object {
  Write-Host " creating $_" 
  pandoc -F pandoc-citeproc --csl din-1505-2-numeric.csl --toc -V toc-title:"Inhaltsverzeichnis" -s -t $_ -o formats/fachartikel.$_ fachartikel.tex
}