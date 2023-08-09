import { BiUserCircle } from "react-icons/bi";
import { Container } from "./styles";

export function Header() {
    return (
        <Container>
            <BiUserCircle className="userIconStyle" />
            <span>Usuário</span>
        </Container>

    );
}