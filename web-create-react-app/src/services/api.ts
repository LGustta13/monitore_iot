import axios from 'axios';

// instância do axios
export const api = axios.create({
    baseURL: 'http://localhost:3001',
});