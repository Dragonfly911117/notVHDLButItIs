const express = require("express");
const app = express();

app.use(express.static('./public'));

app.get("/index", (req, res)=>{
    var response = {
        "my_LED1" : req.query.LED1,
        "my_LED2" : req.query.LED2,
        "my_LED1" : req.query.LED3,
        "my_LED2" : req.query.LED4,
        "my_drone_on" : req.query.drone_on,
        "my_drone_off" : req.query.drone_off,
        "my_inputTimes" : req.query.inputTimes,
        "my_btnShine" : req.query.btnShine
    }
    res.send(response)
})

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log('Serevr is running on port ${PORT}.');
});