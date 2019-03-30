var Tx     = require('ethereumjs-tx')
const Web3 = require('web3')
const web3 = new Web3('https://rinkeby.infura.io/v3/272f7fc703154ec8a6296bbbcf1921f2')

const account1 = '0xC7b42dEbf6793B1290347dA651527228ca8B8BA4' // Your account address 1
const account2 = '0xE638715D5a937Dc57E6D456E8391ddA9Cc45608b' // Your account address 2

const privateKey1 = Buffer.from('89B068DEEBB47B1ABC2EAD4F5CDBE03B84715EDEDC060E26515EB44267810698', 'hex')
const privateKey2 = Buffer.from('F3CD14E971484BE63FE1E6C0F3D784B6C35785A693269D957A9A9281BCF1609B', 'hex')

web3.eth.getTransactionCount(account2, (err, txCount) => {
  // Build the transaction
  const txObject = {
    nonce:    web3.utils.toHex(txCount),
    to:       account1,
    value:    web3.utils.toHex(web3.utils.toWei('0.1', 'ether')),
    gasLimit: web3.utils.toHex(21000),
    gasPrice: web3.utils.toHex(web3.utils.toWei('10', 'gwei'))
  }

  // Sign the transaction
  const tx = new Tx(txObject)
  tx.sign(privateKey2)

  const serializedTx = tx.serialize()
  const raw = '0x' + serializedTx.toString('hex')

  // Broadcast the transaction
  web3.eth.sendSignedTransaction(raw, (err, txHash) => {
    console.log('txHash:', txHash)
    // Now go check etherscan to see the transaction!
  })
})
