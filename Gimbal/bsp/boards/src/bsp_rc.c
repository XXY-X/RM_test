#include "bsp_rc.h"

uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];

/**
 * @brief          ң������ʼ��
 * @param[in]      none
 * @retval         none
 */
void remote_control_init()
{
    RC_Init(sbus_rx_buf[0], sbus_rx_buf[1], SBUS_RX_BUF_NUM);
}

void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
    // enable the DMA transfer for the receiver request
    // ʹ��DMA���ڽ���
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);

    // enalbe idle interrupt
    // ʹ�ܿ����ж�
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

    // disable DMA
    // ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);
    while (hdma_usart3_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart3_rx);
    }

    hdma_usart3_rx.Instance->PAR = (uint32_t) & (USART3->DR);
    // memory buffer 1
    // �ڴ滺����1
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    // memory buffer 2
    // �ڴ滺����2
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(rx2_buf);
    // data length
    // ���ݳ���
    hdma_usart3_rx.Instance->NDTR = dma_buf_num;
    // enable double memory buffer
    // ʹ��˫������
    SET_BIT(hdma_usart3_rx.Instance->CR, DMA_SxCR_DBM);

    // enable DMA
    // ʹ��DMA
    __HAL_DMA_ENABLE(&hdma_usart3_rx);
}

void RC_unable(void)
{
    __HAL_UART_DISABLE(&huart3);
}

void RC_restart(uint16_t dma_buf_num)
{
    __HAL_UART_DISABLE(&huart3);
    __HAL_DMA_DISABLE(&hdma_usart3_rx);

    hdma_usart3_rx.Instance->NDTR = dma_buf_num;

    __HAL_DMA_ENABLE(&hdma_usart3_rx);
    __HAL_UART_ENABLE(&huart3);
}

// �����ж�
void USART3_IRQHandler(void)
{
    if (huart3.Instance->SR & UART_FLAG_RXNE) // ���յ�����
    {
        __HAL_UART_CLEAR_PEFLAG(&huart3);
    }
    else if (USART3->SR & UART_FLAG_IDLE)
    {
        static uint16_t this_time_rx_len = 0;

        __HAL_UART_CLEAR_PEFLAG(&huart3);

        if ((hdma_usart3_rx.Instance->CR & DMA_SxCR_CT) == RESET)
        {
            /* Current memory buffer used is Memory 0 */

            // disable DMA
            // ʧЧDMA
            __HAL_DMA_DISABLE(&hdma_usart3_rx);

            // get receive data length, length = set_data_length - remain_length
            // ��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
            this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

            // reset set_data_lenght
            // �����趨���ݳ���
            hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

            // set memory buffer 1
            // �趨������1
            hdma_usart3_rx.Instance->CR |= DMA_SxCR_CT;

            // enable DMA
            // ʹ��DMA
            __HAL_DMA_ENABLE(&hdma_usart3_rx);

            if (this_time_rx_len == RC_FRAME_LENGTH)
            {
                RemoteReceive(sbus_rx_buf[0]);
            }
        }
        else
        {
            /* Current memory buffer used is Memory 1 */
            // disable DMA
            // ʧЧDMA
            __HAL_DMA_DISABLE(&hdma_usart3_rx);

            // get receive data length, length = set_data_length - remain_length
            // ��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
            this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

            // reset set_data_lenght
            // �����趨���ݳ���
            hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

            // set memory buffer 0
            // �趨������0
            DMA1_Stream1->CR &= ~(DMA_SxCR_CT);

            // enable DMA
            // ʹ��DMA
            __HAL_DMA_ENABLE(&hdma_usart3_rx);

            if (this_time_rx_len == RC_FRAME_LENGTH)
            {
                // ����ң��������
                RemoteReceive(sbus_rx_buf[1]);
            }
        }
    }
}
