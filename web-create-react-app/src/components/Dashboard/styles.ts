import styled from "styled-components";

export const Content = styled.div`

    table {
        width: 85.2%;
        border-spacing: 0 0.2rem;
        padding: 0 1rem;
        margin-bottom: 1rem;

        th {
            color: #969CB3;
            font-weight: 400;
            padding: 1rem 1rem;
            text-align: left;
            line-height: 0.5rem;
        }

        td {
            padding: 0.5rem 1rem;
            border: 0;
            background: #FFFFFF;
            color: #969CB3;
            border-radius: 0.25rem;
            &:first-child {
                color: #363F5F;
            }
        }
    }
`;