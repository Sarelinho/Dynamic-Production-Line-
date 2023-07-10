const express = require("express");
const router = express.Router();
module.exports = router;
const heat_model = require("../models/heat_model");
const isStringOnlyNumbers = (str) => {
  return /^\d+$/.test(str);
};
router.get("/", (req, res) => {
  res.render("heat", {
    item: {},
  });
});
router.post("/", (req, res) => {
  const body = req.body;
  Object.values(body).forEach((item) => {
    if (!isStringOnlyNumbers(item))
      res.status(500).json({ error: "התוכנה מקבלת רק מספרים" });
    if (item < 2) res.status(500).json({ error: "המספר חייב להיות מעל 2" });
  });

  const modelData = new heat_model({
    heat_time: parseInt(`${body.heatTime}`),
    setup_time: parseInt(`${body.setupTime}`),
    test_light: parseInt(`${body.testLight}`),
    delay: parseInt(`${body.delayTime}`),
  });

  modelData.save();
  res.render("heat", {
    item: {},
  });
});

router.get('/get-data/:prossec', async (req, res) => {
  try {
    const heat_model_data = await heat_model.find().sort({ _id: -1 }).limit(1)
    const formattedData = heat_model_data[0]
    console.log(req.params.prossec);
    res.setHeader('Content-Type', 'text/plain');
    res.send(formattedData[req.params.prossec].toString());
  } catch (error) {
    console.error('Error retrieving data:', error);
    res.status(500).send('Error retrieving data');
    }
  });
