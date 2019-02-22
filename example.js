const pledge = require('.')
const fs = require('fs')
const path = require('path')

const buf = Buffer.alloc(32)
const fdFirst = fs.openSync(path.join(__dirname, 'first.txt'), 'as+', 0o555)

pledge('stdio')
// Cannot open new file descriptors now

fs.readSync(fdFirst, buf, 0, 11, 0)
fs.writeSync(fdFirst, Buffer.from('Hello world'), 0)

pledge('')
// Reading or writing here is illegal

fs.closeSync(fdFirst)
