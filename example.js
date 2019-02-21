var pledge = require('.')

console.log('before')
pledge('stdio')
console.log('after')

pledge('')
setTimeout(() => console.log('killed'), 1000)
