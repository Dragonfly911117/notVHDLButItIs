const express = require("express");
const app = express();

app.use(express.static('./public'));

app.get("/index", (req, res)=>{
    var response = {
        "my_LED1" : req.query.LED1,
        "my_LED2" : req.query.LED2,
        "my_LED3" : req.query.LED3,
        "my_LED4" : req.query.LED4,
        "my_drone_on" : req.query.drone_on,
        "my_drone_off" : req.query.drone_off,
        "my_inputTimes" : req.query.inputTimes,
        "my_btnShine" : req.query.btnShine
    }
    controlLED(response)
    res.send("Successfully Requested")
})

function controlLED(object){
    let child_process = require("child_process");
    
    if(object["my_drone_on"] === true){
        if(object["my_LED1"] === true){
            let process = child_process.exeFile('sudo', ["./main LED1 ON"]);
        }
        else if(object["my_LED2"] === true){
            let process = child_process.exeFile('sudo', ["./main LED2 ON"]);
        }
        else if(object["my_LED3"] === true){
            let process = child_process.exeFile('sudo', ["./main LED3 ON"]);
        }
        else if(object["my_LED4"] === true){
            let process = child_process.exeFile('sudo', ["./main LED4 ON"]);
        }
    }
    else if(object["my_drone_off"] === true){
        if(object["my_LED1"] === true){
            let process = child_process.exeFile('sudo', ["./main LED1 OFF"]);
        }
        else if(object["my_LED2"] === true){
            let process = child_process.exeFile('sudo', ["./main LED2 OFF"]);
        }
        else if(object["my_LED3"] === true){
            let process = child_process.exeFile('sudo', ["./main LED3 OFF"]);
        }
        else if(object["my_LED4"] === true){
            let process = child_process.exeFile('sudo', ["./main LED4 OFF"]);
        }
    }
    else if(object["my_btnShine"] === true){
        let process = child_process.exeFile('sudo', ["./main Mode_Shine"], obj["my_inputTimes"]);
    }
    
    process.stdout.on('data', (data) =>{
        console.log(`stdout: ${data}`);
    });
    process.stderr.on('data', (data) =>{
        console.error(`stderr: ${data}`);
    });
    
}

const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`Serevr is running on port ${PORT}.`);
});