const natives = require('rollup-plugin-natives')
const path = require('path')

module.exports = {
        input: './index.js',
        output: [
            {file: path.resolve(__dirname, 'dist', 'index.js')},
        ],
        plugins: [
            natives({
                copyTo: path.resolve(__dirname, 'dist', 'lib'),
                destDir: './lib'
            })
        ]
    }