const express = require('express');
const {exec} = require("child_process");
const router = express.Router();

/* GET users listing. */
router.get('/', async function (req, res, next) {
    let responce = {
        "opt": req.query.toDOrNotToD
    }
    if (responce["opt"] === "YES") {
        res.render('notCool', {title: "jkl"});
    } else {
        res.render('cool', {title: "jkl"});
    }
});

router.get('/notCool', (req, res) => {
    const process = exec(`python ./stuff/test.py`);
    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
        res.send(data)
    });
    process.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
        res.send(data)
    });
});


router.post('/switchLEDs', (req, res) => {
    for (const reqKey in req.body) {
        const process = exec(`./stuff/main ` + reqKey +' '+ req.body[reqKey]);
        process.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        });
        process.stderr.on('data', (data) => {
            console.error(`stderr: ${data}`);
        });
    }
    res.send();
});

router.post('/shineLEDs', (req, res) => {
    for (const reqKey in req.body) {
        const process = exec(`./stuff/main Mode_Shine ` + req.body[reqKey]);
        process.stdout.on('data', (data) => {
            console.log(`stdout: ${data}`);
        });
        process.stderr.on('data', (data) => {
            console.error(`stderr: ${data}`);
        });
    }
    res.send();
});

module.exports = router;
