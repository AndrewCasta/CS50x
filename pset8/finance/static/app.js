// update share price
  symbolBuy = document.querySelector("#symbolBuy")

  symbolBuy.addEventListener('keyup', (e) => {
    shareName = document.querySelector("#shareNameBuy")
    sharePrice = document.querySelector("#sharePriceBuy")
    inputSymbol = e.currentTarget.value
    $.get(`/symbol?symbol=${inputSymbol}`, (data) => {
    shareName.textContent = data.name
    sharePrice.textContent = data.price;
    })
  })

  // calc transaction price
  shareBuy = document.querySelector("#shareBuy")

  shareBuy.addEventListener("keyup", (e) => {
    transactionBuy = document.querySelector("#transactionBuy")
    sharePriceBuy = document.querySelector("#sharePriceBuy")
    shareAmount = e.currentTarget.value
    transactionBuy.textContent = (shareAmount * sharePriceBuy.textContent).toFixed(2)
  })

  // update share price for sell selector
  symbolSell = document.querySelector("#symbolSell")

  symbolSell.addEventListener('change', (e) => {
    shareName = document.querySelector("#shareNameSell")
    sharePrice = document.querySelector("#sharePriceSell")
    inputSymbol = e.currentTarget.value
    $.get(`/symbol?symbol=${inputSymbol}`, (data) => {
    shareName.textContent = data.name
    sharePrice.textContent = data.price;
    })
  })

  // calc transaction price
  shareSell = document.querySelector("#shareSell")

  shareSell.addEventListener("keyup", (e) => {
    transactionSell = document.querySelector("#transactionSell")
    sharePriceSell = document.querySelector("#sharePriceSell")
    shareAmount = e.currentTarget.value
    transactionSell.textContent = (shareAmount * sharePriceSell.textContent).toFixed(2)
  })





/* refactor
  calculation listener
  Putting data-id on the buy and sell container
  Setting evt listener on the parent 'buy-sell'
  Use evt.target
  if (data-id) - if not null it'd be true, i.e. if this is blank it would be falsy?
  Do calc

  // https://css-tricks.com/the-thinking-behind-simplifying-event-handlers/
*/
