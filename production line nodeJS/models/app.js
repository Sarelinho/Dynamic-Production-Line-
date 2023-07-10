const express = require("express");
const mongoose = require("mongoose");
require("dotenv").config();
const app = express();
const port = 3000;
app.use(express.json());
app.use(express.urlencoded());
app.set("view engine", "ejs");

mongoose.connect(process.env.MONGO_STRING);
const database = mongoose.connection;
database.on("error", (error) => {
  console.log(error);
});

database.once("connected", () => {
  console.log("Database nnected");
});

const heat_process = require("./routes/heat_process");
app.use("/heat", heat_process);

app.get("/", (req, res) => {
  res.redirect('/heat');
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
