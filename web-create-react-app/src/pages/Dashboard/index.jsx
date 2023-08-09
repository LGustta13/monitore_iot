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