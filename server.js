let express = require("express");
let bodyParser = require("body-parser");
let app = express();
const http = require("http").createServer(app);
const axios = require("axios");
const options = {
  /* ... */
};
const io = require("socket.io")(http, options);

let urlencodedBodyParser = bodyParser.urlencoded({ extended: true });
app.use(urlencodedBodyParser);

app.use(express.static("public"));

let horoscope = "";
let mood = "";
let color = "";

updateHoroscope();
updateMood();
updateColor();

setInterval(() => {
  updateHoroscope();
  updateMood();
  updateColor();
}, 100000);

function updateHoroscope() {
  axios
    .post("https://aztro.sameerkumar.website/?sign=aries&day=today")
    .then((response) => {
      horoscope = response.data.description;
      console.log(horoscope);
    });
}

function updateMood() {
  axios
    .post("https://aztro.sameerkumar.website/?sign=aries&day=today")
    .then((response) => {
      mood = response.data.mood;
      console.log(mood);
    });
}

function updateColor() {
  axios
    .post("https://aztro.sameerkumar.website/?sign=aries&day=today")
    .then((response) => {
      color = response.data.color;
      console.log(color);
    });
}

const listener = http.listen(process.env.PORT || 3000, process.env.IP, () =>
  console.log("listening on *:3000")
);

io.on("connection", (socket) => {
  console.log("user connected: " + socket.id);
  socket.on("ourMessage", (data) => {
    console.log(data);
    socket.broadcast.emit("returnMessage", { message: "yay!" });
  });
});

app.get("/horoscope", function (req, res) {
  console.log("get horoscope");
  res.send(horoscope);
  io.emit("horoscope", { horoscope: horoscope });
});

app.get("/mood", function (req, res) {
  console.log("get mood");
  res.send(mood);
  io.emit("mood", { mood: mood });
});

app.get("/color", function (req, res) {
  console.log("get color");
  res.send(color);
  io.emit("color", { color: color });
});
