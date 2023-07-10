const mongoose = require('mongoose');

const heatSchema = new mongoose.Schema({
    heat_time: {
        required: true,
        type: Number
    },
    test_light: {
        required: true,
        type: Number
    },
    setup_time: {
        required: true,
        type: Number
    },
    delay: {
        required: true,
        type: Number
    },
});

module.exports = mongoose.model('heat_items', heatSchema)
