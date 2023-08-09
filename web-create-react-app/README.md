"a2075145d3cc47b2b56aeec5e9c78fe7e0055169961b6823629772c96f1f0319",
"2023-04-04 00:00:01",
"2023-04-04 04:40:00"

            {/* <h1>olá</h1>
            <button type="button"><Link to='/dashboard'>Consultar abastecimentos</Link></button>
            <button>Extratos</button> */}

import { Container } from "./styles";
import { Outlet } from 'react-router-dom';

export function Dashboard() {
return (
<Container>
<Outlet />

<h1>Relatório dos abastecimentos</h1>
<h2>A1</h2>
<h2>A2</h2>
</Container>
);
}

import styled from "styled-components";

export const Container = styled.main`    max-width: 1120px;
    margin: 0 auto;
    padding: 2.5rem 1rem;`;
