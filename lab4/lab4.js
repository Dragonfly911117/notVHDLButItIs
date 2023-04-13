const express = require("express");
const app = express();

app.use(express.static('/Users/sunnychan/Desktop/microprocessor/notVHDLButItIs/lab4/public'));
// app.use(express.static('./Users/sunnychan/Desktop/microprocessor/notVHDLButItIs/lab4/public'));

app.get("/index", (req, res) => {
    var response = {
        "my_LED1": req.query.LED1,
        "my_LED2": req.query.LED2,
        "my_LED3": req.query.LED3,
        "my_LED4": req.query.LED4,
        "my_radio": req.query.onOff,
        "my_inputTimes": req.query.inputTimes,
        "my_btnShine": req.query.btnShine
    }
    controlLED(response)
    res.send("Successfully Requested")
})

async function controlLED(object) {
    let child_process = require("child_process");
    let arg;
    let process;
    let list = [];
    console.log(object["my_btnShine"]);
    if (object["my_inputTimes"] !=""){
        list.push("Mode_Shine " + object["my_inputTimes"]);
    }
    else if (object["my_radio"] == 'ON') {
        if (object["my_LED1"] == 'on') {
            list.push("LED1 ON");
        }
        if (object["my_LED2"] == 'on') {
            list.push("LED2 ON");
        }
        if (object["my_LED3"] == 'on') {
            list.push("LED3 ON");
        }
        if (object["my_LED4"] == 'on') {
            list.push("LED4 ON");
        }
    } else if (object["my_radio"] == 'OFF') {
        if (object["my_LED1"] == 'on') {
            arg = "LED1 OFF";
            list.push(arg);
        }
        if (object["my_LED2"] == 'on') {
            arg = "LED2 OFF";
            list.push(arg);
        }
        if (object["my_LED3"] == 'on') {
            arg = "LED3 OFF";
            list.push(arg);
        }
        if (object["my_LED4"] == 'on') {
            arg = "LED4 OFF";
            list.push(arg);
        }
    }
    for (let i = 0; i < list.length; i++) {
        console.log(list[i]);
        process = child_process.exec("./main " + list[i]);
        process.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        });
        process.stderr.on('data', (data) => {
            console.error(`stderr: ${data}`);
        });
        await new Promise(r => setTimeout(r, 500));
    }


}

const PORT = process.env.PORT || 5500;
app.listen(PORT, () => {
    console.log(`Serevr is running on port ${PORT}.`);
});
