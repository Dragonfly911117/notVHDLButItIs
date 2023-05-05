const express = require('express');
const {exec} = require("child_process");
const router = express.Router();

/* GET users listing. */
router.get('/', async function (req, res, next) {
    let responce = {
        "opt": req.query.toDOrNotToD
    }
    if (responce["opt"] === "YES") {
        console.log("fjdkl");
    }
    res.render('cool', {title: "jkl"});
});

router.get('/notCool', (req, res) => {
    const process = exec(`python ./test.py`);
    process.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
        res.send(data)
    });
    process.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
        res.send(data)
    });
});



module.exports = router;
