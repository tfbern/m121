// Web server
const express = require('express')
const app = express()
const webroot = __dirname + '/../client'
app.use(express.static(webroot))
app.listen(80, console.log("Serving GUI on port 80"))


