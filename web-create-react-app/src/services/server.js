// Executar servidor: node server.js

const express = require('express');

const port = 3001;
const app = express();

const cors = require('cors');
app.use(cors());

const axios = require('axios');
app.get('/getAbastecimentos', async (req, res, next) => {
    const { chave, data_inicial, data_final} = req.query;

    if(!chave || !data_inicial || !data_final) return res.status(422).send('chave, datas inicial e final de pesquisa são necessárias');

    try{
        const response = await axios.get(`https://darwin-gps.com.br/api/abastecimentos/getAbastecimentosInternoBomba.php?chave=${chave}&data_inicial=${data_inicial}&data_final=${data_final}`); // Template string
        res.json(response.data);
    } catch (err) {
        res.status(500).json(err.response ? err.response.data : err.message);
    }
})

app.listen(port);
console.log('Server listening...');

