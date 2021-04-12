let socket;
socket = io.connect();

socket.on("mood", (data) => {
  console.log(data);
  document.getElementById("mood").innerText = data.mood;
});

socket.on("horoscope", (data) => {
  console.log(data);
  document.getElementById("horoscope").innerText = data.horoscope;
});

socket.on("color", (data) => {
  console.log(data);
  document.getElementById("color").innerText = data.color;
});
