function calculateCost() {
  const drink = document.getElementById("drink").value;
  const quantity = parseInt(document.getElementById("quantity").value);
  const costField = document.getElementById("cost");

  const prices = {
    tea: 50,
    coffee: 80,
    lemonade: 60
  };

  const cost = prices[drink] * quantity;
  costField.value = `${cost} руб.`;
}

function resetForm() {
  document.getElementById("orderForm").reset();
}
